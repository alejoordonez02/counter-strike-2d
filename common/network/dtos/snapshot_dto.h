#ifndef SNAPSHOT_DTO_H
#define SNAPSHOT_DTO_H

#include "../../snapshot.h"
#include "../dto.h"

class SnapshotDTO : public DTO {
public:
    Snapshot snapshot;

    explicit SnapshotDTO(std::vector<uint8_t>&& bytes) : DTO(std::move(bytes)) {
        deserialize();
    }

    explicit SnapshotDTO(const Snapshot& snap) : DTO(/*tipo de DTO para Snapshot*/), snapshot(snap) {}

    void deserialize() override {
        // Deserializar los datos de payload y llenar snapshot
    }

    void serialize_into(std::vector<uint8_t>& out) override {
        // Serializar los datos de snapshot en out
    }
};

#endif
