#pragma once

#include <QtGlobal>

#pragma pack(push, 1)

struct message_header
{
    quint16 magic;
    quint8 version;
    quint16 message_type;
    quint32 body_length;
};

#pragma pack(pop)

