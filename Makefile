# ---------------------------------------------------------------- DEFAULT GOAL
.DEFAULT_GOAL           := all


# -------------------------------------------------------------- VERBOSE OUTPUT

ifeq ("$(origin V)", "command line")
  ENABLE_VERBOSE        = $(V)
endif
ifndef ENABLE_VERBOSE
  ENABLE_VERBOSE        = 0
endif

ifeq ($(ENABLE_VERBOSE),1)
  Q                     =
else
  Q                     = @
endif


# ------------------------------------------------------------------ META RULES
# This must be included before any meta rules are used
include deps/metamake/Meta.mk


# --------------------------------------------------------- BUILD ARCHITECTURES

$(call BEGIN_DEFINE_ARCH, host_c99, build/host_c99)
  PREFIX        :=
  CF            := -O2 -Wall -Wextra -std=c99
$(call END_DEFINE_ARCH)

$(call BEGIN_DEFINE_ARCH, host_c11, build/host_c11)
  PREFIX        :=
  CF            := -O2 -Wall -Wextra -std=c11
$(call END_DEFINE_ARCH)


# ------------------------------------------------------------- BUILD LIBRARIES

$(call BEGIN_UNIVERSAL_BUILD)
  $(call ADD_C_INCLUDE,         src)
  $(call EXPORT_SHALLOW_DEPS,   timermath)
$(call END_UNIVERSAL_BUILD)

deps_SRC        := $(call FIND_SOURCE_IN_DIR, deps)
$(call BEGIN_UNIVERSAL_BUILD)
  $(call ADD_C_INCLUDE,         deps)
  $(call BUILD_SOURCE,          $(deps_SRC))
  $(call MAKE_LIRARY,           deps)

  $(call EXPORT_SHALLOW_DEPS,   deps)
$(call END_UNIVERSAL_BUILD)


# ----------------------------------------------------------- BUILD EXECUTABLES

test_SRC        := $(call FIND_SOURCE_IN_DIR, test)
$(call BEGIN_UNIVERSAL_BUILD)
  $(call IMPORT_DEPS,           timermath deps)

  $(call BUILD_SOURCE,          $(test_SRC))
  $(call CC_LINK,               timermath_ut)

  # Always build
  $(call EXPORT_SHALLOW_DEPS,   timermath_ut)
  $(call APPEND_ALL_TARGET_VAR)
$(call END_UNIVERSAL_BUILD)


# ---------------------------------------------------------------- GLOBAL RULES

.PHONY: all
all: METAMAKE_ALL
	@echo "===== All build finished ====="

.PHONY: clean
clean: METAMAKE_CLEAN
	@echo "===== Clean finished ====="

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all        - Build all top level targets"
	@echo "  clean      - Clean intermediate build files"
