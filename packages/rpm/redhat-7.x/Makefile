##########################################################################
# Build an RPM from the current spec file and subversion directory tree. #
#                                                                        #
# Note: The RPM and Makefile are set up to GENERATE RPMS as a non-root   #
# user in the user's home directory.  Of course to INSTALL the resulting #
# binary RPM the user has to log in as root.                             #
##########################################################################

SPECFILE := rapidsvn.spec
VERSION_FILE := ../../../src/version.hpp

RPMDIR := rpms

SVN_TOP_DIR := $(shell pwd)/../../..

NAME := $(shell grep '^Name:' < $(SPECFILE) | sed -e 's/^Name: //')
VERSION_MAJOR := $(shell grep 'RAPIDSVN_VER_MAJOR' < $(VERSION_FILE) | (read one two three; echo $$three) )
VERSION_MINOR := $(shell grep 'RAPIDSVN_VER_MINOR' < $(VERSION_FILE) | (read one two three; echo $$three) )
VERSION_MICRO := $(shell grep 'RAPIDSVN_VER_MICRO' < $(VERSION_FILE) | (read one two three; echo $$three) )
VERSION := $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_MICRO)
RELEASE := $(shell svn st -v $(SPECFILE) | cut -b 10- | ( read one two ; echo $$one ) )

SOURCE_RPM_DIR := $(HOME)/$(RPMDIR)/sources/$(NAME)-$(VERSION)-$(RELEASE)

RPMDIRS := \
	$(HOME)/$(RPMDIR) \
	$(HOME)/$(RPMDIR)/build \
	$(HOME)/$(RPMDIR)/rpms \
	$(HOME)/$(RPMDIR)/rpms/i386 \
	$(HOME)/$(RPMDIR)/rpms/i486 \
	$(HOME)/$(RPMDIR)/rpms/i586 \
	$(HOME)/$(RPMDIR)/rpms/i686 \
	$(HOME)/$(RPMDIR)/rpms/noarch \
	$(HOME)/$(RPMDIR)/rpms/ppc \
	$(HOME)/$(RPMDIR)/rpms/sparc \
	$(HOME)/$(RPMDIR)/sources \
	$(HOME)/$(RPMDIR)/srpms \
	$(HOME)/$(RPMDIR)/tmp

all : rpm

rapidsvn rpm : check_release build_srpm_files build_rpm_files

check_release :
	@if [ "$(RELEASE)"x = "x" ]; \
	   then \
		echo "Please specifiy RELEASE"; \
		exit 1 \
	    else \
		exit 0; \
	fi
	@echo "Making $(NAME)-$(VERSION)-$(RELEASE) (S)RPM..."

build_rpm_files : build_srpm_files
	cd $(SOURCE_RPM_DIR); rpmbuild -ba $(SPECFILE)

build_srpm_files : $(HOME)/.rpmmacros $(HOME)/$(RPMDIR) rapidsvn.spec
	rm -rf $(SOURCE_RPM_DIR)
	mkdir -p $(SOURCE_RPM_DIR)
	cp * $(SOURCE_RPM_DIR)
	sed -e 's/@RELEASE@/$(RELEASE)/' \
		-e 's/@VERSION@/$(VERSION)/' \
		< $(SPECFILE) > $(SOURCE_RPM_DIR)/$(SPECFILE)
	cd $(SOURCE_RPM_DIR); cp -r $(SVN_TOP_DIR) $(NAME)-$(VERSION); \
	   tar cfz $(NAME)-$(VERSION)-$(RELEASE).tar.gz $(NAME)-$(VERSION) --exclude .svn; \
	   rm -rf $(NAME)-$(VERSION)

$(HOME)/.rpmmacros : .rpmmacros
	@if [ ! -f $(HOME)/.rpmmacros ]; \
	   then \
	   echo "Creating $(HOME)/.rpmmacros"; \
	   sed -e 's;@RPMSDIR@;$(HOME)/$(RPMDIR);' < .rpmmacros > $(HOME)/.rpmmacros; \
	   fi

$(HOME)/$(RPMDIR) :
	@if [ ! -d $(HOME)/$(RPMDIR) ]; \
		then \
		for i in $(RPMDIRS); \
			do \
			echo "Making directory $$i"; \
			mkdir -p $$i; \
			done; \
	   fi
