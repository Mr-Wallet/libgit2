#include "clar_libgit2.h"
#include "config/config_helpers.h"

static git_repository *_repo;
static git_config *_config;

#define TEST_URL "http://github.com/libgit2/libgit2.git"

void test_remote_list__initialize(void)
{
	cl_fixture_sandbox("testrepo.git");

	cl_git_pass(git_repository_open(&_repo, "testrepo.git"));

	cl_git_pass(git_repository_config(&_config, _repo));
}

void test_remote_list__cleanup(void)
{
	git_config_free(_config);

	git_repository_free(_repo);

	cl_fixture_cleanup("testrepo.git");
}

void test_remote_list__always_checks_disk_config(void)
{
	git_repository *repo2;
	git_remote *remote;
	git_strarray repo1_remote_names, repo2_remote_names;

	cl_git_pass(git_repository_open(&repo2, "testrepo.git"));
	cl_git_pass(git_remote_create(&remote, _repo, "valid-name", TEST_URL));

	cl_git_pass(git_remote_list(&repo1_remote_names, _repo));
	cl_assert_equal_sz(repo1_remote_names.count, 6);

	cl_git_pass(git_remote_list(&repo2_remote_names, repo2));
	cl_assert_equal_sz(repo2_remote_names.count, 6);

	git_strarray_free(&repo1_remote_names);
	git_strarray_free(&repo2_remote_names);
	git_remote_free(remote);
	git_repository_free(repo2);
}
