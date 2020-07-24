# optee-scp03

Foundries.IO SCP03 Control PTA (master branch) or TA (check the ta branch)

To control scp03 via this application, also verify that the following
config has *not* been set:
* CFG_CORE_SE05X_SCP03_EARLY

Also notice that to use scp03_rotate the following config must be set
when building OP-TEE:
 * CFG_CORE_SE05X_SCP03_PROVISION=1

For the TA branch, check the README to load it early if RPMB FS is required.

After installing the binary, do use symbolic links to access to its functionality
* ln -s scp03 scp03_enable
* ln -s scp03 scp03_rotate

