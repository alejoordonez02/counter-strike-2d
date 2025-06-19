#ifndef COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H
#define COMMON_NETWORK_DTOS_SNAPSHOT_DTO_H

#include <utility>
#include <vector>

#include "dto.h"
#include "protocol.h"
#include "snapshot.h"

class SnapshotDTO: public DTO {
public:
    Snapshot snapshot;

    explicit SnapshotDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
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

    void deserialize() override {
        // Deserializar campos snapshot
        int i = 1;  // Start after type byte
        snapshot.round_number = payload[i++];
        size_t num_players = payload[i++];
        snapshot.players.clear();
        snapshot.players.reserve(num_players);
        for (size_t j = 0; j < num_players; ++j) {
            PlayerData player;
            player.player_id = payload[i++];
            player.team_id = payload[i++];
            player.is_walking = payload[i++];
            Position pos = deserialize_pos(i);
            player.x = pos.x;
            player.y = pos.y;
            Position aim = deserialize_pos(i);
            player.aim_x = aim.x;
            player.aim_y = aim.y;
            snapshot.players.push_back(player);
        }
    }

    ~SnapshotDTO() = default;
};

#endif
