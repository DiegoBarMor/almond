import sys
from pathlib import Path
import shutil

SYSTEM_INCLUDES = set()

# ------------------------------------------------------------------------------
def process(line: str) -> "str|None":
    if not line.strip().startswith("#include <"):
        return line
    SYSTEM_INCLUDES.add(line)

# ------------------------------------------------------------------------------
def main():
    shutil.copytree(FOLDER_SRC, FOLDER_DST, dirs_exist_ok = True)
    paths_dst = list(FOLDER_DST.glob("**/*.hpp")) + list(FOLDER_DST.glob("**/*.cpp"))
    for path_dst in paths_dst:
        lines = path_dst.read_text().splitlines()
        out = [line for line in map(process, lines) if line is not None]
        path_dst.write_text("\n".join(out))

    PATH_TXT_INCLUDES.write_text(
        "\n".join(sorted(SYSTEM_INCLUDES)) + '\n'
    )


################################################################################
if __name__ == "__main__":
    FOLDER_SRC = Path(sys.argv[1])
    FOLDER_DST = Path(sys.argv[2])
    PATH_TXT_INCLUDES = FOLDER_DST / "system_includes.txt"
    main()


################################################################################
