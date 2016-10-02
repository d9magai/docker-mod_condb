mod_condb.la: mod_condb.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_condb.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_condb.la

