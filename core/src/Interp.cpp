#include "Interp.h"

template <typename T>
void Interp<T>::step(Interp<T>* This)
{
    if (This->m_endTime > 0)
    {
        Timer::increment(&This->m_timer);

        if (This->m_endTime <= This->m_timer.m_current)
        {
            This->m_timer.set(&This->m_timer, This->m_endTime);
            This->m_endTime = 0;

            if (This->m_method != InterpMethod::CubicHermite)
                return This->m_goal;
        }
    }

    switch (This->m_method)
    {
        case InterpMethod::Linear:
            // "goal" acts as "speed" here.
            This->m_initial += This->m_goal;

        case InterpMethod::Physics:
            // initial = Position
            // bezier2 = Velocity
            // goal    = Acceleration

            This->m_initial += This->m_bezier2; // Pos += Vel
            This->m_bezier2 += This->m_goal;    // Vel += Accel

        case InterpMethod::CubicHermite:
        {
            float t = This->m_timer.m_currentF / (float)This->m_endTime;
            float t2 = t * t;
            float t3 = t2 * t;
            float h00 = (2.0f * t3) - (3.0f * t2) + 1.0f; // H00 = 2t^3 - 3t^2 + 1
            float h10 = t3 - (2.0f * t2) + t;             // H10 = t^3 - 2t^2 + t
            float h01 = (-2.0f * t3) + (3.0f * t2);       // H01 = -2t^3 + 3t^2
            float h11 = t3 - t2;                          // H11 = t^3 - t^2

            T term1 = h00 * This->m_initial; // P0
            T term2 = h10 * This->m_bezier1; // M0
            T term3 = h01 * This->m_goal;    // P1
            T term4 = h11 * This->m_bezier2; // M1
            This->m_initial = term1 + term2 + term3 + term4;
        }

        default:
        {
            float alpha = interpolate(This);
            T delta = This->m_goal - This->m_initial;
            T offset = delta * alpha;
            This->m_initial += offset;
        }
    }
}

template <typename T>
float Interp<T>::interpolate(Interp<T>* This)
{
    float t = m_timer.m_currentF / m_endTime;

    switch(m_method)
    {
    case InterpMethod::In2:
        return pow2(t);
    case InterpMethod::In3:
        return pow3(t);
    case InterpMethod::In4:
        return pow4(t);
    case InterpMethod::Out2:
        return 1.0f - pow2(1.0f - t);
    case InterpMethod::Out3:
        return 1.0f - pow3(1.0f - t);
    case InterpMethod::Out4:
        return 1.0f - pow4(1.0f - t);
    case InterpMethod::InOut2:
        t *= 2.0f;
        if (t < 1.0f) return pow2(t) / 2.0f;
        else return (2.0f - pow2(2.0f - t)) / 2.0f;
    case InterpMethod::InOut3:
        t *= 2.0f;
        if (t < 1.0f) return pow3(t) / 2.0f;
        else return (2.0f - pow3(2.0f - t)) / 2.0f;
    case InterpMethod::InOut4:
        t *= 2.0f;
        if (t < 1.0f) return pow4(t) / 2.0f;
        else return (2.0f - pow4(2.0f - t)) / 2.0f;
    case InterpMethod::OutIn2:
        t *= 2.0f;
        if (t < 1.0f) return 0.5f - pow2(1.0f - t) / 2.0f;
        else return 0.5f + pow2(t - 1.0f) / 2.0f;
    case InterpMethod::OutIn3:
        t *= 2.0f;
        if (t < 1.0f) return 0.5f - pow3(1.0f - t) / 2.0f;
        else return 0.5f + pow3(t - 1.0f) / 2.0f;
    case InterpMethod::OutIn4:
        t *= 2.0f;
        if (t < 1.0f) return 0.5f - pow4(1.0f - t) / 2.0f;
        else return 0.5f + pow4(t - 1.0f) / 2.0f;
    case InterpMethod::Delayed:
        return 0.0f;
    case InterpMethod::Instant:
        return 1.0f;
    default:
        return t;
    }
}