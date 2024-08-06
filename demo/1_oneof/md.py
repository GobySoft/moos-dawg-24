#!/usr/bin/env python3
from rich.console import Console
from rich.markdown import Markdown
import sys

input = ''
for line in sys.stdin:
    input += line

#console = Console()
#md = Markdown(input)
#console.print(md)

print(input)
