if [[ -z $1 ]];then
    echo "Enter the name of the project"
    echo "E.g. ssc hello-world"
    exit 1
fi
sbt new scala/hello-world.g8 --name=$1
echo 'Global / onChangedBuildSource := ReloadOnSourceChanges
libraryDependencies ++= Seq(
"org.scala-lang.modules" %% "scala-parser-combinators" % "1.1.2"
)
lazy val root = (project in file(".")) // Determines the baseDirectory
    .settings(
        scalaVersion := "2.13.3",
        name := "default", // Change this to whatever you want
        version := "0.0.0",
        Compile / mainClass := Some("Main"), // The name of your Main File
        assembly / mainClass := Some("Main"),
        // Sweet Sweet Compile Warnings
        Compile / console / scalacOptions := Seq(
        "-language:_", "-depreciation","-Xlint", "-Ywarm-unused",
        "-Yawrn-dead-code", "-explaintypes", "opt:_", "-Xdev")
    )'\
> $1/build.sbt
echo 'addSbtPlugin("com.eed3si9n" % "sbt-assembly" % "0.15.0")' > $1/project/plugins.sbt
cd $1
echo "------------------------------------------------------------"
echo "                  S B T    C O M M A N D S"
echo "------------------------------------------------------------"
echo "sbt run: Runs your project"
echo "sbt compile: Compiles your project"
echo "sbt assembly: Creates a jar file. Works with Java and Scala
If you use Java run: java -jar target/scala-2.13/default-assembly-0.0.0.jar"
