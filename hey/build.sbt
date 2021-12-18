Global / onChangedBuildSource := ReloadOnSourceChanges
libraryDependencies ++= Seq(
"org.scala-lang.modules" %% "scala-parser-combinators" % "1.1.2"
)
lazy val root = (project in file(".")) // Determines the baseDirectory
    .settings(
        scalaVersion := "2.13.3",
        name := "default", // Change this to whatever you want
        version := "0.0.0",
        Compile / mainClass := Some("com.hey.Main"), // The name of your Main File
        assembly / mainClass := Some("com.hey.Main"),
        // Sweet Sweet Compile Warnings
        Compile / console / scalacOptions := Seq(
        "-language:_", "-depreciation","-Xlint", "-Ywarm-unused",
        "-Yawrn-dead-code", "-explaintypes", "opt:_", "-Xdev")
    )
