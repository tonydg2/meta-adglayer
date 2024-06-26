# ~/.bashrc: executed by bash(1) for non-login shells.

export PS1='\h:\w\$ '
#export PS1="\[\033[32m\]\W\[\033[33m\]\$(parse_git_branch)\[\033[00m\]>"
umask 022

###############
## ADG BASHRC!
###############
# You may uncomment the following lines if you want `ls' to be colorized:
export LS_OPTIONS='--color=auto'
eval `dircolors`
alias ls='ls $LS_OPTIONS'
alias ll='ls $LS_OPTIONS -l'
alias l='ls $LS_OPTIONS -lA'

alias cl="clear"
alias cls="cl;ls"



# Some more alias to avoid making mistakes:
# alias rm='rm -i'
# alias cp='cp -i'
# alias mv='mv -i'
