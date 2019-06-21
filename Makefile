#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := TagoIO


COMPONENT_ADD_INCLUDEDIRS := platform
#COMPONENT_ADD_INCLUDEDIRS := $(PROJECT_PATH)/Headers/platform
#COMPONENT_ADD_INCLUDEDIRS := $(PROJECT_PATH)/Headers/tasks


#COMPONENT_SRCDIRS := platform/wifi
#COMPONENT_SRCDIRS := platform/board_init
#EXTRA_COMPONENT_DIRS = $(IDF_PATH)/examples/common_components/protocol_examples_common


include $(IDF_PATH)/make/project.mk

