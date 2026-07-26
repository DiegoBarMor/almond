import sys
from pathlib import Path

# ------------------------------------------------------------------------------
def fix_spacing(data: str) -> str:
    lines = data.splitlines()
    if not lines: return data
    return '\n'.join(
        f"    {line}" if i else f" {line}"
        for i,line in enumerate(lines)
    )


# ------------------------------------------------------------------------------
def extract_definitions(data_cpp: str) -> dict[str, str]:
    idx = 0
    buffer = data_cpp
    definitions = {}
    while buffer:
        idx = buffer.find("FUNC@", idx)
        if idx == -1: break

        buffer = buffer[idx + len("FUNC@"):]
        if not buffer: break

        name = buffer.split()[0]
        buffer = buffer[len(name):]

        idx = buffer.find("\n")
        buffer = '{' + buffer[idx:]

        idx = buffer.find(f"END@{name}")
        if idx == -1:
            print(f"XXX Missing END@{name}")
            exit(-1)

        if name in definitions:
            print(f"XXX Duplicate definition: {name}")
            exit(-1)

        definitions[name] = fix_spacing(buffer[:idx].rstrip(" \n/"))

    return definitions


# ------------------------------------------------------------------------------
def apply_definitions(data_hpp: str, definitions: dict[str, str]) -> str:
    out = []
    buffer = data_hpp
    while buffer:
        idx = buffer.find("HEAD@")
        if idx == -1:
            out.append(buffer)
            break

        before = buffer[:idx].rstrip("; /")
        after = buffer[idx + len("HEAD@"):]
        if not after:
            out.append(buffer)
            break

        name = after.split()[0]
        if name not in definitions:
            print(f"XXX Missing definition: {name}")
            exit(-1)

        out.append(before + definitions[name])
        buffer = after[len(name):]

    return "\n".join(out) + "\n"


# ------------------------------------------------------------------------------
def merge_files(path_cpp: Path, path_hpp: Path) -> str:
    data_cpp = path_cpp.read_text()
    data_hpp = path_hpp.read_text()

    defs = extract_definitions(data_cpp)
    merged = apply_definitions(data_hpp, defs)
    return merged


# ------------------------------------------------------------------------------
def save_hpp_packed(path_hpp: Path, data: str):
    path_out = FOLDER_OUT / path_hpp.relative_to(FOLDER_SRC)
    path_out.parent.mkdir(parents = True, exist_ok = True)
    path_out.write_text(data)


# ------------------------------------------------------------------------------
def main():
    paths_cpp = list(FOLDER_SRC.glob("**/*.cpp"))
    paths_hpp = set(FOLDER_SRC.glob("**/*.hpp"))
    for path_cpp in paths_cpp:
        path_hpp = path_cpp.with_suffix(".hpp")
        if path_hpp not in paths_hpp:
            print(f"XXX Missing header file: {path_hpp}")
            exit(-1)

        save_hpp_packed(path_hpp, merge_files(path_cpp, path_hpp))
        paths_hpp.remove(path_hpp)

    for path_hpp in paths_hpp:
        save_hpp_packed(path_hpp, path_hpp.read_text())


################################################################################
if __name__ == "__main__":
    FOLDER_SRC = Path(sys.argv[1])
    FOLDER_OUT = Path(sys.argv[2])
    main()


################################################################################
