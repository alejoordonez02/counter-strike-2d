
#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/player_commands/command.h"

void mock_server(Queue<Snapshot>& queue) {
    int tick = 0;
    while (tick < 10) {
        Snapshot snap;
        // Simula un jugador moviéndose en diagonal
        PlayerDTO player;
        player.player_id = 1;
        snprintf(player.player_name, MAX_PLAYER_NAME, "Jugador1");
        player.x = 100 + tick * 2;
        player.y = 100 + tick * 2;
        player.facing_angle = (tick * 10) % 360;
        
        snap.players.push_back(player);

        queue.push(snap);

        tick++;
    }
}
