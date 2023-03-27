#!/usr/bin/env python3
import sys
import regex
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import cli


@cli.command(
    cli.arg("--to", dest="to", default="HEAD", action="store", type=str,
            help="specify explicitly the end commit where to parse to."),
    cli.arg("--from", dest="from", default="main", action="store", type=str,
            help="specify explicitly the begin commit where to parse from."),
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    formatter_class=RawTextHelpFormatter,
    name="check", prog=CHECK_SCRIPT_NAME,
    help=fixedWidth(
        "generate the commit diff message.",
        width=60
    ),
    description=fixedWidth(
        f'A script to generate the changelog message.'
    )
)
def ldtCheck(args):
    LOG = prompt.Log.getInstance(verbose=getattr(args, "verbose"))
    ARG_COMMIT_TO = getattr(args, "to")
    ARG_COMMIT_FROM = getattr(args, "from")

    LOG.log("get revision hash from {} to {}.",
            LOG.format(ARG_COMMIT_FROM, flag=LOG.HIGHTLIGHT),
            LOG.format(ARG_COMMIT_TO, flag=LOG.HIGHTLIGHT))

    CMD = ["git", "-C", PROJECT_ROOT, "rev-list", f"{ARG_COMMIT_FROM}..{ARG_COMMIT_TO}"]
    hashes = []
    with launchSubprocess(CMD) as proc:
        out, _ = proc.communicate()
        if proc.wait() != 0:
            LOG.failure("failed to get revision from {} to {}.",
                        LOG.format(ARG_COMMIT_FROM, flag=LOG.HIGHTLIGHT),
                        LOG.format(ARG_COMMIT_TO, flag=LOG.HIGHTLIGHT))
            return proc.returncode
        hashes += out.splitlines()

    solution_commit: list[tuple[str, str]] = []
    features_commit: list[tuple[str, str]] = []

    COMMIT_FORMAT = regex.compile("^([a-z\d]{7})(?: \([^)]+\))? ([^\n]+)$")
    SOLUTION_FORMAT = regex.compile("^adds q(\d+) ")
    for rev in hashes:
        CMD = ["git", "-C", PROJECT_ROOT, "show", "--quiet", "--oneline", rev]
        out, _ = launchSubprocess(CMD).communicate()
        commit_match = COMMIT_FORMAT.match(out)
        sha = commit_match.group(1)
        msg = commit_match.group(2)
        if SOLUTION_FORMAT.search(msg):
            solution_commit.append((sha, msg))
        else:
            features_commit.append((sha, msg))

    weeks_cnt = int((TODAY - PROJECT_INITIAL_DATE).days / 7)
    title_msg = ""
    detail_msg = ""
    if len(solution_commit) > 0:
        title_msg += "adds {} solution(s)".format(
            LOG.format(len(solution_commit), flag=LOG.HIGHTLIGHT))
        detail_msg += f"add solution(s) details:\n"
        for rev, msg in solution_commit:
            detail_msg += "  {} {}\n".format(
                LOG.format(rev, flag=LOG.HIGHTLIGHT), msg)
    if len(features_commit) > 0:
        title_msg += "{}modifies {} feature(s)".format(
            ", " if len(solution_commit) else "",
            LOG.format(len(features_commit), flag=LOG.HIGHTLIGHT))
        detail_msg += "\nmodifies/fixes:\n"
        for rev, msg in features_commit:
            detail_msg += "  {} {}\n".format(
                LOG.format(rev, flag=LOG.HIGHTLIGHT), msg)

    if title_msg != "":
        title_msg += " in week {}.\n".format(LOG.format(weeks_cnt,
                                                      flag=LOG.HIGHTLIGHT))

    LOG.print(title_msg)
    LOG.print(detail_msg)
    return 0

if __name__ == "__main__":
    sys.exit(safeRun(ldtCheck))
