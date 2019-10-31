from conans import ConanFile, CMake, tools


class TestrapidmessageConan(ConanFile):
    name = "test_async_pqxx"
    version = "0.1"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Testrapidmessage here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    required = "async_pqxx/0.1.6@firstinversion/testing"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        self.run("./bin/test")
