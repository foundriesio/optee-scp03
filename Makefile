export V ?= 0

OUTPUT_DIR := $(CURDIR)/out

.PHONY: all
all: scp03-target prepare-for-rootfs

.PHONY: clean
clean: scp03-clean prepare-for-rootfs-clean

scp03-target:
	@echo "Building scp03"
	$(MAKE) -C scp03 CROSS_COMPILE="$(HOST_CROSS_COMPILE)" || exit -1

scp03-clean:
	@echo "Cleaning scp03"
	$(MAKE) -C scp03 clean || exit -1;

prepare-for-rootfs: scp03-target
	@echo "Copying scp03 CA  to $(OUTPUT_DIR)..."
	@mkdir -p $(OUTPUT_DIR)
	@mkdir -p $(OUTPUT_DIR)/ca
	if [ -e scp03/host/scp03 ]; then \
		cp -p scp03/host/scp03 $(OUTPUT_DIR)/ca/; \
	fi

prepare-for-rootfs-clean:
	@rm -rf $(OUTPUT_DIR)/ca
	@rmdir --ignore-fail-on-non-empty $(OUTPUT_DIR) || test ! -e $(OUTPUT_DIR)
