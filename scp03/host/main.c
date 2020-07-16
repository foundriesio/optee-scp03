/*
 * Copyright (c) 2020, Foundries.IO
 */

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <tee_client_api.h>
#include <ta_scp03.h>

#define CMD_ENABLE "scp03_enable"
#define CMD_ROTATE "scp03_rotate"

struct scp03_ctx {
	TEEC_Context ctx;
	TEEC_Session sess;
};

void prepare_tee_session(struct scp03_ctx *ctx)
{
	TEEC_UUID uuid = TA_SCP03_UUID;
	uint32_t origin;
	TEEC_Result res;

	res = TEEC_InitializeContext(NULL, &ctx->ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);

	res = TEEC_OpenSession(&ctx->ctx, &ctx->sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, origin);
}

void terminate_tee_session(struct scp03_ctx *ctx)
{
	TEEC_CloseSession(&ctx->sess);
	TEEC_FinalizeContext(&ctx->ctx);
}

static int scp03_enable(unsigned int rotate_keys)
{
	struct scp03_ctx ctx;
	TEEC_Operation op;
	TEEC_Result res;
	uint32_t origin;

	prepare_tee_session(&ctx);

	memset(&op, 0, sizeof(op));
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = rotate_keys;

	res = TEEC_InvokeCommand(&ctx.sess, TA_CRYPT_CMD_ENABLE_SCP03,
				 &op, &origin);

	terminate_tee_session(&ctx);

	if (res == TEEC_SUCCESS)
		return 0;
		
	fprintf(stderr, "scp03 request failed: 0x%x / %u\n", res, origin);

	return -1;
}

int main(int argc, char *argv[])
{
	char *p, *cmdname = *argv;

	if ((p = strrchr (cmdname, '/')) != NULL)
		cmdname = p + 1;

	if (!strncmp(cmdname, CMD_ROTATE, strlen(CMD_ROTATE))) {
		if (scp03_enable(1)) {
			fprintf (stderr, "Cant rotate scp03 keys\n");
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	if (!strncmp(cmdname, CMD_ENABLE, strlen(CMD_ENABLE))) {
		if (scp03_enable(0)) {
			fprintf (stderr, "Cant enable scp03\n");
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	fprintf (stderr,
		"Identity crisis - may be called as `" CMD_ENABLE
		"' or as `" CMD_ROTATE "' but not as `%s'\n", argv[0]);

	return EXIT_FAILURE;
}
