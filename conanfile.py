from conans import ConanFile, CMake, tools


class BeastMode(ConanFile):
    name = "async_pqxx"
    version = "0.1.0"
    license = "MIT"
    author = ("Andrew Rademacher <andrewrademacher@icloud.com>")
    url = "https://bitbucket.org/firstinversion/async_pqxx/"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake"
    exports_sources = "*"
    requires = ("boost/1.71.0@conan/stable",
                "libpqxx/6.4.5@bincrafters/stable")
    build_requires = ("Catch2/2.9.1@catchorg/stable",)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.build()
            cmake.test()

    def package(self):
        self.copy("**/*", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["async_pqxx"]
