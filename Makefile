all:
	@cd ${PLANCK_SRC}; sensei -o ${PLANCK_BUILD_STAGE}
	@ninja -C ${PLANCK_BUILD_STAGE}
	
clean:
	@ninja -C ${PLANCK_BUILD_STAGE} -t clean
