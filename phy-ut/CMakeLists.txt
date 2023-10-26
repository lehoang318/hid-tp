project(phy-ut)

add_executable(${PROJECT_NAME}
    phy_ut.c
    $<TARGET_OBJECTS:CTRL_PHY>
)
