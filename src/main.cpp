#include <string>
#include <vector>

#include "keys_generator.hpp"
#include "encryptor_decryptor.hpp"
#include "parse_source.hpp"


void show_usage(const std::string &name)
{
    std::cerr << "usage: " << name << '\n'
              << "\t-h, --help\n"
              << "\t--gen-keys=path_for_keys\n"
              << "\t--key=pub_key_path --encrypt=file_path\n"
              << "\t--key=priv_key_path --decrypt=file_path\n";
}


int main(int argc, char *argv[])
{
    std::vector<RSA::SourceString> sources {};

    for (int i {0}; i < argc; ++i) {
        sources.emplace_back(argv[i]);
    }

    RSA::KeysGenerator keys_generator;

    switch (parse_sources(argc, sources)) {
        case RSA::Option::GenKeys:
            return !keys_generator.gen_keys(sources[1].path());
        case RSA::Option::Encrypt:
            return !RSA::encrypt(sources[1].path(), sources[2].path());
        case RSA::Option::Decrypt:
            return !RSA::decrypt(sources[1].path(), sources[2].path());
        case RSA::Option::Unknow:
            show_usage(sources[0].str());
    }

    return -1;
}
