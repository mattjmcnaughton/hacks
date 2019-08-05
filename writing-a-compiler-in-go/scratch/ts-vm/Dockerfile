FROM node

WORKDIR /code

RUN npm install typescript -S
RUN npm install -g ts-node

ENTRYPOINT ["ts-node", "virtual_machine.ts"]
