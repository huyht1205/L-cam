include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${DRIVERS_DIR}/pmu/nxp/pf1550
    )

set(PMU_SOURCES
    ${DRIVERS_DIR}/pmu/pmu.cpp
    ${DRIVERS_DIR}/pmu/nxp/pf1550/pf1550.cpp
    )