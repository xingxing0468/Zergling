FROM silkeh/clang:10

LABEL maintainer="RafikFarhad<rafikfarhad@gmail.com>"

COPY clang_format_entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]