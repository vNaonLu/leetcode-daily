import sys
from argparse import RawTextHelpFormatter
# prevent generating __pycache__
sys.dont_write_bytecode = True

from utils import *
import cli


@cli.command(
    formatter_class=RawTextHelpFormatter,
    name="update", prog=UPDATE_SCRIPT_NAME,
    help=fixedWidth(
        f"update the project documents and diagrams.",
        width=60
    ),
    description=fixedWidth(
        f'A nested script to request and update the questions list and update the readme and '
        f'resolve diagrams including activities and progress SVG.'
    )
)
def ldtUpdate(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--src", dest="src_path", default=str(SRC_ABSOLUTE), action="store",
            metavar="[Source_Root]", help="specify the source root."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to save created assets."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to save created documents."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="all", prog=UPDATE_ALL_SCRIPT_NAME,
    help=fixedWidth(
        f"update all things which the project has changed.",
        width=60
    ),
    description=fixedWidth(
        f'A simple script to combine the features |{UPDATE_README_SCRIPT_NAME}|, '
        f'|{UPDATE_QUESTIONS_LIST_SCRIPT_NAME}| and |{UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME}|.'
    )
)
def UpdateAll(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--list", dest="questions_list_file", default=str(QUESTIONS_LIST_ABSOLUTE), action="store",
            nargs=1, metavar="[Ques_List]", help="specify the questions list in CSV format."),
    cli.arg("--resolve", dest="questions_log_file", default=str(QUESTIONS_LOG_ABSOLUTE), action="store",
            nargs=1, metavar="[Solve_Log]", help="specify the resolve log in CSV format."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to load resolve status."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to load documents."),
    cli.arg("readme_path", metavar="Target", nargs=1, type=str, help="target file to update."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="readme", prog=UPDATE_README_SCRIPT_NAME,
    help=fixedWidth("update the readme document.", width=60 ),
    description=fixedWidth('Update the readme document.')
)
def UpdateReadme(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("questions_list", metavar="Target", nargs=1, type=str, help="target file to update."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="list", prog=UPDATE_QUESTIONS_LIST_SCRIPT_NAME,
    help=fixedWidth("request and update the questions list.", width=60 ),
    description=fixedWidth('Request and update the questions list.')
)
def UpdateQuestionsList(args: object):
    pass


@cli.command(
    cli.arg("-v", "--verbose", dest="verbose", default=False, action="store_true",
            help="enable verbose logging."),
    cli.arg("--assets", dest="assets_path", default=str(ASSETS_ABSOLUTE), action="store",
            nargs=1, metavar="[Assets_path]", help="specify the directory to save created assets."),
    cli.arg("--docs", dest="docs_path", default=str(DOCS_ABSOLUTE), action="store",
            nargs=1, metavar="[Docs_path]", help="specify the directory to save created documents."),
    formatter_class=RawTextHelpFormatter,
    parent=ldtUpdate, name="diagrams", prog=UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME,
    help=fixedWidth("update the resolve diagrams and documents.", width=60 ),
    description=fixedWidth('Update the resolve diagrams and documents.')
)
def UpdateResolveDiagrams(args: object):
    pass


if __name__ == "__main__":
    sys.exit(ldtUpdate())
