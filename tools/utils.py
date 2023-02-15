import textwrap
from pathlib import Path

SCRIPT_NAME = "LeetCodeDailyTools"
CAT_SCRIPT_NAME = f"{SCRIPT_NAME}_Cat"
ADD_SCRIPT_NAME = f"{SCRIPT_NAME}_Add"
REMOVE_SCRIPT_NAME = f"{SCRIPT_NAME}_Remove"
UPDATE_SCRIPT_NAME = f"{SCRIPT_NAME}_Update"
UPDATE_ALL_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_All"
UPDATE_README_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_Readme"
UPDATE_QUESTIONS_LIST_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_QuestionsList"
UPDATE_RESOLVE_DIAGRAMS_SCRIPT_NAME = f"{UPDATE_SCRIPT_NAME}_ResolveStatus"
PROJECT_ROOT = Path(__file__).parent.resolve()
SRC_RELATIVE = Path('./src')
DOCS_RELATIVE = Path('./docs')
ASSETS_RELATIVE = Path('./assets')
SRC_ABSOLUTE = PROJECT_ROOT.joinpath(SRC_RELATIVE).resolve()
DOCS_ABSOLUTE = PROJECT_ROOT.joinpath(DOCS_RELATIVE).resolve()
ASSETS_ABSOLUTE = PROJECT_ROOT.joinpath(ASSETS_RELATIVE).resolve()
QUESTIONS_LOG_ABSOLUTE = SRC_ABSOLUTE.joinpath("logs.csv")
QUESTIONS_LIST_ABSOLUTE = SRC_ABSOLUTE.joinpath("questions_list.csv")

def concat(*args, delimiter: str = '\n'):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return str(*args)
    return delimiter.join(*args)

def fixedWidth(*args, width: int = 80):
    if len(args) == 0:
        return ""
    elif len(args) == 1 and isinstance(*args, str):
        return concat(textwrap.wrap(*args, width, break_long_words=False))
        
    res = []
    for s in args:
        res.append(concat(textwrap.wrap(s, width, break_long_words=False)))
    return concat(res)

if __name__ == "__main__":
    print("PROJECT_ROOT", str(PROJECT_ROOT))
    print("SRC_ABSOLUTE", str(SRC_ABSOLUTE))
    print("DOCS_ABSOLUTE", str(DOCS_ABSOLUTE))
    print("ASSETS_ABSOLUTE", str(ASSETS_ABSOLUTE))
    a = fixedWidth(
        'A script to manage LeetCode Daily project, including automatically adding'
        'the unsolved questions, generating the C++ solution template based on the'
        'code snippet queried from LeetCode.'
    )
    print(a)