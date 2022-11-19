import argparse


class Recipe:
    def __init__(self) -> None:
        self.c_sources = list[str]()
        self.c_include = list[str]()
        self.c_libs = list[str]()
        self.c_defs = list[str]()
        self.mcu = list[str]()
        self.ldscript = str()

    def to_cmake(self) -> str:
        cmake = str()

        cmake += "set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/%s)\n" % (
            self.ldscript)
        cmake += "\n"

        cmake += Recipe.create_cmake_list("set(BSP_SOURCES\n", self.c_sources)
        cmake += "\n"

        cmake += Recipe.create_cmake_list(
            "include_directories(\n",
            self.c_include,
            remove=[' ', '-I'])
        cmake += "\n"

        cmake += Recipe.create_cmake_list("set(MCU_OPTS\n", self.mcu)
        cmake += "\n"

        cmake += "add_link_options(\n"
        cmake += "\t${MCU_OPTS}\n"
        cmake += "\t-T ${LINKER_SCRIPT}\n"
        cmake += "\t)\n"
        cmake += "\n"

        self.c_defs.append("${MCU_OPTS}")
        cmake += "\n"

        cmake += Recipe.create_cmake_list(
            "add_compile_options(\n", self.c_defs)
        cmake += "\n"

        return cmake

    @staticmethod
    def create_cmake_list(
            header: str, content: list[str],
            remove=[' '], footer="\t)\n") -> str:
        result = header
        for c in content:
            for s in remove:
                c = c.strip(s)
            result += "\t%s\n" % (c)
        result += footer

        return result

    @staticmethod
    def from_cubemx_makefile(makefile_path: str):
        makefile = dict[str, list[str]]()
        recipe = Recipe()
        with open(makefile_path, 'r') as f:
            rawData = f.read()

        rawData = rawData.replace('\\\n', ',').split('\n')
        for line in rawData:
            if '=' not in line:
                continue
            line = line.split(' = ')
            key = line[0]

            if key not in makefile.keys():
                makefile[key] = line[1:]
            else:
                makefile[key] += line[1:]

        recipe.mcu = Recipe.parse_makefile_mcu(makefile)
        recipe.c_sources = Recipe.parse_path_list(makefile, 'C_SOURCES')
        recipe.c_sources += Recipe.parse_path_list(makefile, 'ASM_SOURCES')
        recipe.c_include = Recipe.parse_path_list(makefile, 'C_INCLUDES')
        recipe.c_libs = Recipe.parse_path_list(makefile, 'LIBS', separator=' ')
        recipe.c_defs = Recipe.parse_path_list(makefile, 'C_DEFS')
        recipe.ldscript = makefile['LDSCRIPT'][0]

        return recipe

    @ staticmethod
    def parse_makefile_mcu(makefile: dict[str, list[str]]) -> list[str]:
        mcu = makefile['MCU'][0]
        mcu = mcu.replace('$(CPU)', makefile['CPU'][0])
        mcu = mcu.replace('$(FPU)', makefile['FPU'][0])
        mcu = mcu.replace('$(FLOAT-ABI)', makefile['FLOAT-ABI'][0])
        mcu = mcu.split(' ')

        return mcu

    @ staticmethod
    def parse_path_list(
            makefile: dict[str, list[str]],
            target: str, separator=',') -> list[str]:
        line = makefile[target][0].split(separator)
        if line[0] == ' ':
            return line[1:]
        else:
            return line


if __name__ == '__main__':
    parse = argparse.ArgumentParser()

    parse.add_argument('f', help='Makefile path')

    args = parse.parse_args()

    recipe = Recipe.from_cubemx_makefile(args.f)
    print(recipe.to_cmake())
