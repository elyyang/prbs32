##############################################################################################################
#
# ELY 2024
#
##############################################################################################################

VERBOSE = TRUE
SOURCE_NAME = source  
TARGET = prbs32

##############################################################################################################

# paths
PROJECT_ROOT := $(realpath ./)
SOURCE_ROOT := $(PROJECT_ROOT)
BUILD_ROOT := $(PROJECT_ROOT)
SOURCE_DIRS = $(addsuffix /source, $(PROJECT_ROOT))
BUILD_DIRS = $(addsuffix /build, $(PROJECT_ROOT))
INCLUDES = $(foreach index, $(SOURCE_DIRS), $(addprefix -I , $(index)/include))
# add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCE_DIRS)
# sources  
SOURCES = $(foreach index, $(SOURCE_DIRS), $(wildcard $(index)/*.c $(index)/*.cpp))
SOURCES += $(PROJECT_ROOT)/main.cpp
# object and dependencies
OBJECTS := $(subst $(SOURCE_ROOT), $(BUILD_ROOT), $(SOURCES))
OBJECTS := $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(OBJECTS)))
DEPENDECIES = $(OBJECTS:.o=.d)

##############################################################################################################

# Compiler (gcc or g++)
CC = gcc 

# Compile Flags
CFLAGS = -Wall   	\
		 -Werror	\
		 -g

##############################################################################################################

# helpers
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP = /
# Remove space after separator
PSEP = $(strip $(SEP))
# Verbosity
ifeq ($(VERBOSE),TRUE)
    HIDE =  
else
    HIDE = @
endif

##############################################################################################################

# Note: make all will execute the following recipe in sequence: "directories", "$(TARGET)" 
all: directories $(TARGET)
	@echo "Done" $@ 

$(TARGET):
	@echo "[Building...]"
	$(HIDE)$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(TARGET).bin

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIRS)) $(ERRIGNORE)

# Clean up
clean:
	@echo "[Cleaning...]"
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(BUILD_DIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET).* $(ERRIGNORE)
	@echo "Done" $@ 

# dump vars for debug purposes
debug:
	@echo "SOURCE_DIRS"
	@echo $(SOURCE_DIRS)
	@echo "BUILD_DIRS"
	@echo $(BUILD_DIRS)
	@echo "INCLUDES"
	@echo $(INCLUDES)
	@echo "SOURCES"
	@echo $(SOURCES)
	@echo "OBJECTS"
	@echo $(OBJECTS)
	@echo "DEPENDECIES"
	@echo $(DEPENDECIES)	
	@echo "RULES"
	@echo $(RULES)
	@echo "Done" $@
