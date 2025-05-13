#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <cstdint>
#include <vector>

class Serializable {
public:
    virtual std::vector<uint8_t> serialize() const = 0;
    virtual ~Serializable() {}
};

#endif
