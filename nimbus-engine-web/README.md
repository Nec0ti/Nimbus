# Nimbus Engine (Web Prototype)

This is a web-based prototype of the Nimbus Engine editor and runtime, showcasing a Unity-like UI and a basic 3D scene using Three.js.

## Run

From this folder:

```bash
# Option 1: Python 3 http.server
python3 -m http.server 8080 --bind 0.0.0.0

# Option 2: Node http-server (if installed)
# npx http-server -p 8080 -a 0.0.0.0
```

Then open your browser to:

- http://localhost:8080/nimbus-engine-web/index.html

## Features
- Menu bar, toolbar, hierarchy, scene view, inspector, project window
- Object selection and transform editing in inspector
- Play/pause with simple cube and sphere animation
- View modes: shaded, wireframe, textured (stub)
- Basic scene stats (tris, draw calls)

## Next steps
- Add gizmo handles for move/rotate/scale
- Add asset importers and persistence
- Add docking/layout saving
- Migrate to a modular TypeScript codebase
