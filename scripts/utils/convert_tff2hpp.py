import sys
from pathlib import Path

################################################################################
if __name__ == "__main__":
    path_tff = Path(sys.argv[1])
    name = path_tff.stem
    name = name.replace('.', '_').replace('-', '_')
    path_hpp = path_tff.parent / f"font_{name}.hpp"

    with open(path_tff, "rb") as f:
        tff = f.read()

    curly_0 = '{'; curly_1 = '}'
    buffer = '\n'.join((
        "#pragma once",
        f"inline std::size_t size_{name} = {len(tff)};",
        f"const uint8_t tff_{name}[{len(tff)}] = {curly_0}{','.join(hex(x) for x in tff)}{curly_1};"
    ))

    with open(path_hpp, "w") as f:
        f.write(buffer)

    print(f"Generated: {path_hpp}")


################################################################################
