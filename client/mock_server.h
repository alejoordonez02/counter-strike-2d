
#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../server/player_commands/command.h"

void mock_server(Queue<Snapshot>& queue) {
    int tick = 0;
    while (tick < 10) {
        Snapshot snap;
        snap.round_number = 1 + tick;
        // Simula un jugador moviéndose en diagonal
        PlayerDTO player_id_2;
        player_id_2.player_id = 2;
        snprintf(player_id_2.player_name, MAX_PLAYER_NAME, "Jugador2");
        player_id_2.x = 100 + tick * 2;
        player_id_2.y = 100 + tick * 2;
        player_id_2.facing_angle = (tick * 10) % 360;
        snap.players.push_back(player_id_2);
        
        PlayerDTO player_id_1;
        player_id_1.player_id = 1;
        player_id_1.x = 0;
        player_id_1.y = 0;
        snap.players.push_back(player_id_1);

        queue.try_push(snap);

        tick++;
    }
}
