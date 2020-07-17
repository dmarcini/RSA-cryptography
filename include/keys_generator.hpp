#ifndef KEYS_GENERATOR_HPP_
#define KEYS_GENERATOR_HPP_

#include <string>
#include <cstdint>
#include <utility>


namespace RSA {

class KeysGenerator {
public:
    using Key = std::pair<std::int_fast64_t, std::int_fast64_t>;

    KeysGenerator() = default;
    ~KeysGenerator() = default;

    KeysGenerator(const KeysGenerator&) = delete;
    KeysGenerator& operator=(const KeysGenerator&) = delete;
    KeysGenerator(KeysGenerator&&) = delete;
    KeysGenerator& operator=(KeysGenerator&&) = delete;

    // generate and save the keys in the specified location
    // (by default in the folder where the binary files is placed)
    bool gen_keys(const std::string &path = "");
private:
    bool gen_pub_key(const std::string &path = "");
    bool gen_priv_key(const std::string &path = "");

    bool save_key(const std::string &path,
                  const std::string &key_name, const Key &key);

    // value of euler function
    std::int_fast64_t phi_ {};
    // module of euler function
    std::int_fast64_t n_ {};

    Key pub_key_ {};
    Key priv_key_ {};
};

}; // namespace RSA

#endif // KEYS_GENERATOR_HPP_
