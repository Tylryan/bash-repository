sbt new scala/hello-world.g8 -o $1
echo '
Global / onChangedBuildSource := ReloadOnSourceChanges
libraryDependencies ++= Seq(
"org.scala-lang.modules" %% "scala-parser-combinators" % "1.1.2"
)
lazy val any_name = (project in file(".")) // Determines the baseDirectory
    .settings(
        scalaVersion := "2.13.3",
        name := "any_name_too",
        version := "1.0",
        Compile / mainClass := Some("Main"), // The name of your Main File
        assembly / mainClass := Some("Main"),
        // Sweet Sweet Compile Warnings
        Compile / console / scalacOptions := Seq(
        "-language:_", "-depreciation","-Xlint", "-Ywarm-unused",
        "-Yawrn-dead-code", "-explaintypes", "opt:_", "-Xdev")
    )' > $1/build.sbt
echo 'addSbtPlugin("com.eed3si9n" % "sbt-assembly" % "0.15.0")' > $1/project/plugins.sbt
