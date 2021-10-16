venv:
	if [ ! -d ".venv" ]; then python3 -m venv .venv; fi
	. .venv/bin/activate && pip3 install -r requirements.txt
	. .venv/bin/activate && pip3 install -r dev-requirements.txt

shell:
	. .venv/bin/activate && ipython
