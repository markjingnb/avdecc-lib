/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2015 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * stream_port_input_get_audio_map_response_imp.cpp
 *
 * STREAM PORT INPUT get clock source response implementation
 */

#include "enumeration.h"
#include "log_imp.h"
#include "stream_port_input_get_audio_map_response_imp.h"
#include "util.h"

namespace avdecc_lib
{
stream_port_input_get_audio_map_response_imp::stream_port_input_get_audio_map_response_imp(uint8_t * frame, size_t frame_len, ssize_t pos)
{
    m_position = pos;
    m_size = frame_len;
    m_frame = (uint8_t *)malloc(m_size * sizeof(uint8_t));
    memcpy(m_frame, frame, m_size);

    offset = m_position + JDKSAVDECC_AEM_COMMAND_GET_AUDIO_MAP_RESPONSE_OFFSET_MAPPINGS + (8 * map_index());

    for (unsigned int i = 0; i < (unsigned int)number_of_mappings(); i++)
    {
        struct stream_port_input_audio_mapping map;

        map.stream_index = jdksavdecc_uint16_get(frame, offset);
        map.stream_channel = jdksavdecc_uint16_get(frame, offset + 2);
        map.cluster_offset = jdksavdecc_uint16_get(frame, offset + 4);
        map.cluster_channel = jdksavdecc_uint16_get(frame, offset + 6);
        maps.push_back(map);
        offset += sizeof(struct stream_port_input_audio_mapping);
    }
}

stream_port_input_get_audio_map_response_imp::~stream_port_input_get_audio_map_response_imp()
{
    free(m_frame);
}

uint16_t stream_port_input_get_audio_map_response_imp::map_index()
{
    return jdksavdecc_aem_command_get_audio_map_response_get_map_index(m_frame, m_position);
}

uint16_t stream_port_input_get_audio_map_response_imp::number_of_mappings()
{
    return jdksavdecc_aem_command_get_audio_map_response_get_number_of_mappings(m_frame, m_position);
}

int STDCALL stream_port_input_get_audio_map_response_imp::mapping(size_t index, struct stream_port_input_audio_mapping & map)
{
    if (index >= number_of_mappings())
        return -1;

    map = maps.at(index);
    return 0;
}
}
