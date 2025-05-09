#!/usr/bin/env python3
import sys
import regex
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
from impl import *
import dcli


def getCommand(parent=None):
    @dcli.command(
        "check",
        dcli.arg("--to", dest="to", default="HEAD", action="store", type=str,
                 help="specify explicitly the end commit where to parse to."),
        dcli.arg("--from", dest="from", default="main", action="store", type=str,
                 help="specify explicitly the begin commit where to parse from."),
        dcli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
                 help="enable verbose logging."),
        parent=parent,
        formatter_class=RawTextHelpFormatter,
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

        CMD = ["git", "-C", PROJECT_ROOT, "rev-list",
               f"{ARG_COMMIT_FROM}..{ARG_COMMIT_TO}"]
        hashes = []
        with launchSubprocess(CMD) as proc:
            out, _ = proc.communicate()
            if proc.wait() != 0:
                LOG.failure("failed to get revision from {} to {}.",
                            LOG.format(ARG_COMMIT_FROM, flag=LOG.HIGHTLIGHT),
                            LOG.format(ARG_COMMIT_TO, flag=LOG.HIGHTLIGHT))
                return proc.returncode
            hashes += out.splitlines()

        adding_commit: list[tuple[str, str]] = []
        modify_commit: list[tuple[str, str]] = []
        features_commit: list[tuple[str, str]] = []

        COMMIT_FORMAT = regex.compile("(\w*) (.*)")
        ADDING_FORMAT = regex.compile("^adds q(\d+)")
        MODIFY_FORMAT = regex.compile("^modifies q(\d+)")
        for rev in hashes:
            CMD = ["git", "-C", PROJECT_ROOT,
                   "log", "-1", "--pretty=%H %B", rev]
            out, _ = launchSubprocess(CMD).communicate()
            commit_match = COMMIT_FORMAT.search(out)
            sha = commit_match.group(1)
            msg = commit_match.group(2)
            if ADDING_FORMAT.search(msg):
                adding_commit.append((sha, msg))
            elif MODIFY_FORMAT.search(msg):
                modify_commit.append((sha, msg))
            else:
                features_commit.append((sha, msg))

        weeks_cnt = int((TODAY - PROJECT_INITIAL_DATE).days / 7)
        title_msg = ""
        detail_msg = ""
        if len(adding_commit) > 0:
            title_msg += "adds {} solution(s)".format(
                LOG.format(len(adding_commit), flag=LOG.HIGHTLIGHT))
            detail_msg += f"add solution(s):\n"
            for rev, msg in adding_commit:
                detail_msg += "  {} {}\n".format(
                    LOG.format(rev, flag=LOG.HIGHTLIGHT), msg)
        if len(modify_commit) > 0:
            title_msg += "{}modifies {} solution(s)".format(
                ", " if len(adding_commit) else "",
                LOG.format(len(modify_commit), flag=LOG.HIGHTLIGHT))
            detail_msg += f"\nmodify solution(s):\n"
            for rev, msg in modify_commit:
                detail_msg += "  {} {}\n".format(
                    LOG.format(rev, flag=LOG.HIGHTLIGHT), msg)
        if len(features_commit) > 0:
            detail_msg += "\nother modification(s):\n"
            for rev, msg in features_commit:
                detail_msg += "  {} {}\n".format(
                    LOG.format(rev, flag=LOG.HIGHTLIGHT), msg)

        if title_msg != "":
            title_msg += " in week {}.\n".format(LOG.format(weeks_cnt,
                                                            flag=LOG.HIGHTLIGHT))

        LOG.print(title_msg)
        LOG.print(detail_msg)
        return 0

    return ldtCheck


if __name__ == "__main__":
    sys.exit(safeRun(getCommand()))
