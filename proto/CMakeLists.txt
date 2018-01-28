find_package(Protobuf REQUIRED)

if (PYTHON)
protobuf_generate_python( PROTO_PY
    telemetry.proto
)
add_custom_target(generate_proto ALL DEPENDS ${PROTO_PY})
else()
protobuf_generate_cpp( PROTO_SRCS PROTO_HDRS
    telemetry.proto
)

add_library( telemetry_proto STATIC
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(telemetry_proto
    ${Protobuf_LIBRARIES}
)
endif(PYTHON)
