FROM gcc:latest

WORKDIR /
RUN mkdir -p proj output

WORKDIR /proj
COPY . .
RUN make

WORKDIR /output
RUN cp /proj/build/* . && rm -rf /proj
COPY run_all.sh .
RUN chmod +x run_all.sh

CMD ["./run_all.sh"]
