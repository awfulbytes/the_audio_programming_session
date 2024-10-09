# To use the "confirm" target inside another target,
# use the " if $(MAKE) -s confirm ; " syntax.
mycommand:
	@if $(MAKE) -s confirm ; then \
    	     execute_your_command_here ; \
	fi
.PHONY: mycommand

# The CI environment variable can be set to a non-empty string,
# it'll bypass this command that will "return true", as a "yes" answer.
confirm:
	@if [[ -z "$(CI)" ]]; then \
		REPLY="" ; \
        printf $(_WARN) "BE AWARE TURN DOWN SPEAKERS!!..!!" ;\
		read -p "⚠ Are you sure? I will play the sound you created [y/n] > " -r ; \
		if [[ ! $$REPLY =~ ^[Yy]$$ ]]; then \
			printf $(_ERROR) "KO" "Stopping" ; \
			exit 1 ; \
		else \
			printf $(_TITLE) "OK" "Continuing" ; \
			exit 0; \
		fi \
	fi
.PHONY: confirm
_WARN := "\033[33m[%s]\033[0m %s\n"  # Yellow text for "printf"
_TITLE := "\033[32m[%s]\033[0m %s\n" # Green text for "printf"
_ERROR := "\033[31m[%s]\033[0m %s\n" # Red text for "printf"
