#ifndef CLIENT_Q_GAME_DETAILS_DTO_H
#define CLIENT_Q_GAME_DETAILS_DTO_H

#include <string>
#include <vector>
#include <cstdint>
#include <QMetaType>
#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/map_name.h"
#include "common/network/dtos/game_details_dto.h"

class QGameDetailsDTO {
private:
    std::string name;
    uint8_t tt_count;
    uint8_t ct_count;
    MapName map_name;
    bool _is_joinable;

public:
    QGameDetailsDTO(GameDetailsDTO&& d): name(d.name), tt_count(d.tt_count),
            ct_count(d.ct_count), map_name(d.map_name),
            _is_joinable(d._is_joinable) {}

    QGameDetailsDTO() = default;
    
    const std::string& getName() const { return name; }
    uint8_t getTtCount() const { return tt_count; }
    uint8_t getCtCount() const { return ct_count; }
    MapName getMapName() const { return map_name; }
    bool isJoinable() const { return _is_joinable; }

    QGameDetailsDTO(const QGameDetailsDTO&) = default;
    QGameDetailsDTO& operator=(const QGameDetailsDTO&) = default;
    
    QGameDetailsDTO(QGameDetailsDTO&&) = default;
    QGameDetailsDTO& operator=(QGameDetailsDTO&&) = default;
    

    ~QGameDetailsDTO() = default;
};

Q_DECLARE_METATYPE(QGameDetailsDTO)
Q_DECLARE_METATYPE(QSharedPointer<QGameDetailsDTO>)
#endif