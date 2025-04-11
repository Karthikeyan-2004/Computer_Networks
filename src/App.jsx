import React from 'react';
import Counter from './Counter';
import './App.css';
import User from './User';
const App = () => {
  return (
    <div className="App">
      <h1>Counter App</h1>
      <Counter />
      <User />
    </div>
  );
}
export default App;
