TOP_DIR		= .

LCFLAGS += -I$(TOP_DIR)/base
LCFLAGS += -I$(TOP_DIR)/inc
LCFLAGS += -I$(TOP_DIR)/inc/base
LCFLAGS += -I$(TOP_DIR)/inc/utils
LCFLAGS += -I$(TOP_DIR)/inc/study
LCFLAGS += -I$(TOP_DIR)/inc/com
LCFLAGS += -I$(TOP_DIR)/test/com
#LCFLAGS += -I$(TOP_DIR)/core
#LCFLAGS += -I$(TOP_DIR)/runtime
#LCFLAGS += -I$(TOP_DIR)/tools
#LCFLAGS += -I$(TOP_DIR)/tools/CodeGen
#LCFLAGS += -I$(TOP_DIR)/tools/Analysis
#LCFLAGS += -I$(TOP_DIR)/tools/TestMode
LCFLAGS += -lpthread

SUBDIRS		=\
		src \
		base \
		utils \
		study \
		test \
		test/com \


include $(TOP_DIR)/mk/target.mk
