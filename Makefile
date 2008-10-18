# Directories and output file
SRC_DIR = src
XML_SRC_DIR = $(SRC_DIR)/xsd
DOC_DIR = doc
OBJ_DIR = obj
OUTFILE = mtp2lastfm

# Compiling stuff
CC      = @g++
LD      = @g++
XSD     = @xsd
CFLAGS  = -Wall -g
LDFLAGS = -Wall -g -lmtp -lcurl -lxerces-c

# Extra commands
ECHO    = @echo
DOXYGEN = @doxygen
TEST    = @if test

# Object files
BASE    := main track device scrobbler md5 utils
OBJECTS := $(addprefix $(OBJ_DIR)/, $(BASE))


all: xml-binary $(OBJECTS)
	$(ECHO) "[LD] $(OUTFILE)"
	$(LD) $(LDFLAGS) $(addsuffix .o, $(OBJECTS)) $(OBJ_DIR)/mtp2lastfm.o -o $(OUTFILE)

$(OBJECTS): bin-dir
	$(ECHO) "[CC] $@"
	$(CC) $(CFLAGS) -c $(subst $(OBJ_DIR),$(SRC_DIR), $@).cpp -o $@.o

bin-dir:
	$(TEST) -d $(OBJ_DIR); then true; else mkdir $(OBJ_DIR); fi

xml-source:
	$(ECHO) "[XSD] XML binding generation"
	$(XSD) cxx-tree --generate-serialization --root-element mtp2lastfm \
		--output-dir $(XML_SRC_DIR) --namespace-map =xml \
		$(XML_SRC_DIR)/mtp2lastfm.xsd

xml-binary: bin-dir xml-source
	$(ECHO) "[CC] obj/mtp2lastfm"
	$(CC) $(CFLAGS) -c $(XML_SRC_DIR)/mtp2lastfm.cxx -o $(OBJ_DIR)/mtp2lastfm.o

documentation: clean-doc
	$(ECHO) "Building new documentation..."
	$(TEST) -d $(DOC_DIR); then true; else mkdir $(DOC_DIR); fi
	$(DOXYGEN) $(SRC_DIR)/Doxyconf > /dev/null
	$(ECHO) "Done!"


# Cleaning stuff
clean:
	$(TEST) -e $(OUTFILE); then rm -f $(OUTFILE); else true; fi
	$(TEST) -d $(OBJ_DIR); then rm -rf $(OBJ_DIR); else true; fi
	$(TEST) -d $(XML_SRC_DIR); then rm -rf $(XML_SRC_DIR)/*xx; else true; fi

clean-doc:
	$(ECHO) "Cleaning old doc dir..."
	$(TEST) -d $(DOC_DIR); then rm -rf $(DOC_DIR); else true; fi
