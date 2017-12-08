#include <cstdio>
#include <cstdlib>

#include <git2.h>

static void check_error(int error_code, const char *msg)
{
	if (!error_code)
		return;

	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int error;

	git_libgit2_init();

	git_repository *repo = NULL;
	error = git_repository_open(&repo, ".");
	check_error(error, "opening repository");

	git_revwalk *revwalk;

	error = git_revwalk_new(&revwalk, repo);
	check_error(error, "creating revwalk");

	error = git_revwalk_push_head(revwalk);
	check_error(error, "filling revwalk");

	git_oid oid;
	while (git_revwalk_next(&oid, revwalk) == 0) {
		char id[GIT_OID_HEXSZ+1];
		git_oid_tostr(id, sizeof(id), &oid);
		printf("%s\n", id);
	}

	printf("Bye.\n");
	return EXIT_SUCCESS;
}
