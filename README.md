# optee-scp03
Foundries.IO SCP03 Control TA

When building OP-TEE make sure to include the TA in the tree:
 * CFG_IN_TREE_EARLY_TAS=scp03/86a5c8d3-3961-4606-b90e-c116499d1b54

To control scp03 via this application, also verify that the following
config has *not* been set:
* CFG_CORE_SE05X_SCP03_EARLY

Also notice that to use scp03_rotate the following config must be set
when building OP-TEE:
 * CFG_CORE_SE05X_SCP03_PROVISION=1

