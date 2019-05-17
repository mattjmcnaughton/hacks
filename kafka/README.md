# kafka

Experiments with kafka - running it locally. For now, experiment with kafka-go
library from segment.io.

`docker run -p 2181:2181 -p 9092:9092 --env TOPICS=myTopic --env ADVERTISED_HOST=localhost --env ADVERTISED_PORT=9092 spotify/kafka`
