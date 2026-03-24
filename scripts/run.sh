if PROJECT_DIR="$(git rev-parse --show-toplevel 2>/dev/null)"; then
  :
else
  SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
fi

cd "$PROJECT_DIR/bin/Debug"

LANG=ja_JP.UTF-8 LC_ALL=ja_JP.UTF-8 WINEPREFIX=~/.wine32 WINEDLLOVERRIDES="d3d9=n,b" wine th11.exe