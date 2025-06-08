#ifndef SNAPSHOT_DTO_H
#define SNAPSHOT_DTO_H

#include "../../snapshot.h"
#include "../dto.h"
#include "../protocol.h"

class SnapshotDTO : public DTO {
public:
    Snapshot snapshot;

    explicit SnapshotDTO(std::vector<uint8_t>&& bytes)
        : DTO(std::move(bytes)) {
        deserialize();
    }

    explicit SnapshotDTO(const Snapshot& snap)
        : DTO(DTOSerial::GameState::SNAPSHOT), snapshot(snap) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        // TODO: Serializar campos snapshot
    }

    void deserialize() override {
        // TODO: Deserializar campos snapshot
    }

    ~SnapshotDTO() = default;
};

#endif