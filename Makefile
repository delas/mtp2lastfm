# Directories and output file
SRC_DIR = src
DOC_DIR = doc
OBJ_DIR = obj
OUTFILE = mtp2lastfm

# Compiling stuff
CC      = @g++
LD      = @g++
CFLAGS  = -Wall -g
LDFLAGS = -Wall -g -lmtp

# Extra commands
ECHO    = @echo
DOXYGEN = @doxygen
TEST    = @if test

# Object files
BASE    := main track device scrobbler
OBJECTS := $(addprefix $(OBJ_DIR)/, $(BASE))


all: $(OBJECTS)
	$(ECHO) "[LD] $(OUTFILE)"
	$(LD) $(LDFLAGS) $(addsuffix .o, $(OBJECTS)) -o $(OUTFILE)

$(OBJECTS): bin-dir
	$(ECHO) "[CC] $@"
	$(CC) $(CFLAGS) -c $(subst $(OBJ_DIR),$(SRC_DIR), $@).cpp -o $@.o

bin-dir:
	$(TEST) -d $(OBJ_DIR); then true; else mkdir $(OBJ_DIR); fi

documentation: clean-doc
	$(ECHO) "Building new documentation..."
	$(TEST) -d $(DOC_DIR); then true; else mkdir $(DOC_DIR); fi
	$(DOXYGEN) $(SRC_DIR)/Doxyconf > /dev/null
	$(ECHO) "Done!"


# Cleaning stuff
clean:
	$(TEST) -e $(OUTFILE); then rm -f $(OUTFILE); else true; fi
	$(TEST) -d $(OBJ_DIR); then rm -rf $(OBJ_DIR); else true; fi

clean-doc:
	$(ECHO) "Cleaning old doc dir..."
	$(TEST) -d $(DOC_DIR); then rm -rf $(DOC_DIR); else true; fi
