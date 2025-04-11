import React, { useState } from 'react';

function User() {
  const [form, setForm] = useState({ name: '', email: '' });

  const handleChange = e => {
    setForm({ ...form, [e.target.name]: e.target.value });
  };

  const handleSubmit = e => {
    e.preventDefault();
    console.log('Form Submitted:', form);
  };

  return (
    <form onSubmit={handleSubmit}>
      <input name="name" onChange={handleChange} value={form.name} placeholder="Name" />
      <input name="email" onChange={handleChange} value={form.email} placeholder="Email" />
      <button type="submit">Submit</button>
    </form>
  );
}
export default User;





// ### ✅ 1. **Counter App with `useState`**
// ```jsx
// import React, { useState } from 'react';

// function Counter() {
//   const [count, setCount] = useState(0);

//   return (
//     <div>
//       <p>Count: {count}</p>
//       <button onClick={() => setCount(count + 1)}>Increment</button>
//     </div>
//   );
// }
// ```

// ---

// ### ✅ 2. **Fetching API Data using `useEffect`**
// ```jsx
// import React, { useEffect, useState } from 'react';

// function Users() {
//   const [users, setUsers] = useState([]);

//   useEffect(() => {
//     fetch('https://jsonplaceholder.typicode.com/users')
//       .then(res => res.json())
//       .then(data => setUsers(data));
//   }, []);

//   return (
//     <ul>
//       {users.map(user => <li key={user.id}>{user.name}</li>)}
//     </ul>
//   );
// }
// ```

// ---

// ### ✅ 3. **Form Handling with Controlled Inputs**
// ```jsx
// import React, { useState } from 'react';

// function ContactForm() {
//   const [form, setForm] = useState({ name: '', email: '' });

//   const handleChange = e => {
//     setForm({ ...form, [e.target.name]: e.target.value });
//   };

//   const handleSubmit = e => {
//     e.preventDefault();
//     console.log('Form Submitted:', form);
//   };

//   return (
//     <form onSubmit={handleSubmit}>
//       <input name="name" onChange={handleChange} value={form.name} placeholder="Name" />
//       <input name="email" onChange={handleChange} value={form.email} placeholder="Email" />
//       <button type="submit">Submit</button>
//     </form>
//   );
// }
// ```

// ---

// ### ✅ 4. **Conditional Rendering Example**
// ```jsx
// function Greeting({ isLoggedIn }) {
//   return (
//     <div>
//       {isLoggedIn ? <h2>Welcome Back!</h2> : <h2>Please Log In</h2>}
//     </div>
//   );
// }
// ```

// ---

// ### ✅ 5. **React Router Basic Navigation**
// ```jsx
// // App.js
// import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';

// function Home() { return <h2>Home</h2>; }
// function About() { return <h2>About</h2>; }

// function App() {
//   return (
//     <BrowserRouter>
//       <nav>
//         <Link to="/">Home</Link> | <Link to="/about">About</Link>
//       </nav>

//       <Routes>
//         <Route path="/" element={<Home />} />
//         <Route path="/about" element={<About />} />
//       </Routes>
//     </BrowserRouter>
//   );
// }
// ```

// ---

// ### ✅ 6. **Lift State Up (Parent ↔ Child communication)**
// ```jsx
// function Child({ count }) {
//   return <h3>Child Count: {count}</h3>;
// }

// function Parent() {
//   const [count, setCount] = useState(0);
//   return (
//     <div>
//       <Child count={count} />
//       <button onClick={() => setCount(count + 1)}>Increment</button>
//     </div>
//   );
// }
// ```

// ---

// ### ✅ 7. **To-Do List Example**
// ```jsx
// function TodoApp() {
//   const [task, setTask] = useState('');
//   const [tasks, setTasks] = useState([]);

//   const addTask = () => {
//     if (task) {
//       setTasks([...tasks, task]);
//       setTask('');
//     }
//   };

//   return (
//     <div>
//       <input value={task} onChange={e => setTask(e.target.value)} />
//       <button onClick={addTask}>Add</button>
//       <ul>
//         {tasks.map((t, idx) => <li key={idx}>{t}</li>)}
//       </ul>
//     </div>
//   );
// }
// ```

// ---

// ### ✅ 8. **React Redux Example (Minimal)**
// ```jsx
// // counterSlice.js
// import { createSlice } from '@reduxjs/toolkit';

// const slice = createSlice({
//   name: 'counter',
//   initialState: { value: 0 },
//   reducers: {
//     increment: state => { state.value += 1; }
//   }
// });

// export const { increment } = slice.actions;
// export default slice.reducer;
// ```

// ```jsx
// // CounterComponent.js
// import React from 'react';
// import { useDispatch, useSelector } from 'react-redux';
// import { increment } from './counterSlice';

// function CounterComponent() {
//   const dispatch = useDispatch();
//   const count = useSelector(state => state.counter.value);

//   return (
//     <div>
//       <h3>{count}</h3>
//       <button onClick={() => dispatch(increment())}>+</button>
//     </div>
//   );
// }
// ```

// ---