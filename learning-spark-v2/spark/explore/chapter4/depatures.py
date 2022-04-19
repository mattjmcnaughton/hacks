import os

from pyspark.sql import SparkSession
from pyspark.sql.functions import col, desc


if __name__ == "__main__":
    spark = SparkSession.builder.appName("SparkSQLExampleApp").getOrCreate()

    csv_file = f"{os.path.dirname(os.path.realpath(__file__))}/data/departuredelays.csv"
    df = (
        spark.read.format("csv")
        .option("inferSchema", "true")
        .option("header", "true")
        .load(csv_file)
    )

    # Assign name for table in spark sql
    df.createOrReplaceTempView("us_delay_flights_tbl")

    spark.sql(
        """SELECT distance, origin, destination FROM us_delay_flights_tbl
    WHERE distance > 1000 ORDER BY distance DESC"""
    ).show(10)

    spark.sql(
        """SELECT date, delay, origin, destination
    FROM us_delay_flights_tbl
    WHERE delay > 120 AND ORIGIN = 'SFO' AND DESTINATION = 'ORD'
    ORDER BY delay DESC"""
    ).show(10)

    (
        df.select("distance", "origin", "destination")
        .where(col("distance") > 1000)
        .orderBy(desc("distance"))
    ).show(10)
