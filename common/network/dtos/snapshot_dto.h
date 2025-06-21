#ifndef COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H
#define COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H

#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/snapshot.h"

class SnapshotDTO: public DTO {
private:
    // Snapshot snapshot;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        // Deserializar campos snapshot
        in++;  // skip 1st byte (DTO type)
        snapshot.round_number = *in++;
        size_t num_players = *in++;
        snapshot.players.clear();
        snapshot.players.reserve(num_players);
        for (size_t j = 0; j < num_players; ++j) {
            PlayerData player;
            player.player_id = *in++;
            player.team_id = *in++;
            player.is_walking = *in++;
            Position pos = deserialize_pos_from(in);
            player.x = pos.x;
            player.y = pos.y;
            Position aim = deserialize_pos_from(in);
            player.aim_x = aim.x;
            player.aim_y = aim.y;
            snapshot.players.push_back(player);
        }
    }

public:
    Snapshot snapshot;

    explicit SnapshotDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit SnapshotDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::SNAPSHOT) {
        deserialize_from(in);
    }

    explicit SnapshotDTO(const Snapshot& snap):
            DTO(DTOSerial::PlayerCommands::SNAPSHOT), snapshot(snap) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        // Serializar campos snapshot
        out.push_back(snapshot.round_number);

        // jugadores
        out.push_back(snapshot.players.size());
        for (const auto& player : snapshot.players) {
            out.push_back(player.player_id);
            out.push_back(player.team_id);
            out.push_back(player.is_walking);
            serialize_tuple_into(out, player.x, player.y);
            serialize_tuple_into(out, player.aim_x, player.aim_y);
        }
    }

    ~SnapshotDTO() = default;
};

#endif
