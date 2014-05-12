ObjSuf        = o
SrcSuf        = cpp
ExeSuf        = run

DEFINES       = 

CXX           = g++
CXXFLAGS      = --std=c++0x
CXXFLAGS      += -O -Wall -fPIC $(DEFINES) -Wno-unused-result -Wshadow
CXXFLAGS      += -I./

LDFLAGS       = -g -O -Wall -fPIC -Wl,--no-undefined 
SOFLAGS       = -shared

# You'll need libsnd to compile.
# If you don't have it : apt-get install libsndfile1-dev
LIBS          = -lsndfile

# Uncomment this line if you want to use a script to parse & colorize gcc output
# (You can also export this variable from your bashrc)
#GCCPARSER     = 2>&1 | python ~/littleScripts/colorGcc.py

#------------------------------------------------------------------------------
SOURCES       = $(wildcard *.$(SrcSuf))
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
EXECUTABLES   = $(SOURCES:.$(SrcSuf)=.$(ExeSuf))
#------------------------------------------------------------------------------
DEFAULT_TARGET = main
#------------------------------------------------------------------------------

all: compile run
	
compile: $(DEFAULT_TARGET).$(ExeSuf)

run:
	./$(DEFAULT_TARGET).$(ExeSuf) | tee $(DEFAULT_TARGET).log

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(EXECUTABLES)

#------------------------------------------------------------------------------

$(DEFAULT_TARGET).$(ExeSuf): $(DEFAULT_TARGET).$(SrcSuf)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(LIBS) $(GCCPARSER)

